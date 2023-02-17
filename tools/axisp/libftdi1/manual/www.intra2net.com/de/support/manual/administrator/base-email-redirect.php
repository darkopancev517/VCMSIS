<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Weiterleitung von gesamten Domains | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-email.php" title="15. Kapitel - E-Mail"><link rel="prev" href="base-email-receive.php" title="15.3. E-Mail-Empfang auf dem Intranator"><link rel="next" href="base-email-addressing.php" title="15.5. E-Mail-Adressierung">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="base-email-redirect.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-email-redirect.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">15.4. Weiterleitung von gesamten Domains</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-email-receive.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">15. Kapitel - E-Mail</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-email-addressing.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-email-redirect"></a>15.4. Weiterleitung von gesamten Domains</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-redirect-concept"></a>15.4.1. Konzept</h3></div></div></div><a class="indexterm" name="base-email-redirect-domain1"></a><a class="indexterm" name="base-email-redirect-domain2"></a><a class="indexterm" name="base-email-redirect-domain3"></a><p>Bei jeder Domain besteht die M&ouml;glichkeit, die E-Mails nicht an die Benutzer des
        Intranators zuzustellen, sondern sie einem anderen Mail- oder Groupwareserver (z.B.
        Microsoft Exchange oder Lotus Domino) zu &uuml;bergeben. Diese Weiterleitung erfolgt nach der
        Pr&uuml;fung auf Viren, verbotene Anh&auml;nge und dem globalen Spamfilter.</p><p>Unter Dienste&nbsp;&gt;&nbsp;E-Mail&nbsp;&gt;&nbsp;Domains&nbsp;:&nbsp;Weiterleitung
        kann diese Weiterleitung f&uuml;r jede Domain eingerichtet werden.</p><p>Es besteht die M&ouml;glichkeit, die Zieldomain der weitergeleiteten E-Mails zu &auml;ndern. Wenn
        Sie also z.B. die Domain <strong class="userinput"><code>beispiel.de</code></strong> auf dem Intranator empfangen und
        bei <span class="guimenuitem">Domain Adress&auml;nderung</span>
        <strong class="userinput"><code>xyz.de</code></strong> eintragen, werden die Zieladressen in allen weitergeleiteten
        E-Mails auf ...@xyz.de abge&auml;ndert. Dies ist vor allem dann hilfreich, wenn der Zielserver
        nicht umkonfiguriert werden soll.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-redirect-adresschecking"></a>15.4.2. Empf&auml;ngeradresspr&uuml;fung</h3></div></div></div><a class="indexterm" name="base-email-redirect-adresschecking1"></a><p>Kann eine E-Mail nicht zugestellt werden, muss der Absender mit einer
        Nichtzustellbarkeits-Nachricht (<span class="foreignphrase"><em class="foreignphrase">Bounce</em></span>) dar&uuml;ber informiert
        werden. Dies gilt nat&uuml;rlich auch f&uuml;r den Fall, dass zwar die Zieldomain vorhanden ist, aber
        nicht der Benutzer. Sollten Spammer in kurzer Zeit viele E-Mails an ung&uuml;ltige Empf&auml;nger
        senden, kann dieser Mechanismus zu 2 Problemen f&uuml;hren:</p><div class="itemizedlist"><ul type="disc"><li><p>Jede dieser Nichtzustellbarkeits-E-Mails muss an den Absender zugestellt werden und
            erzeugt dadurch Last. Au&szlig;erdem sind bei Spam viele Absenderadressen auch wieder falsch
            und dadurch wird von der anderen Seite wieder eine Nichtzustellbarkeits-Nachricht
            erzeugt, (<span class="foreignphrase"><em class="foreignphrase">Double-Bounce</em></span>) was die Last weiter
            erh&ouml;ht.</p></li><li><p>Einige Empf&auml;nger betrachten Nichtzustellbarkeits-Antworten auf E-Mails, die nicht
            von ihnen selbst stammen, als Spam. Kommen davon zu viele in kurzer Zeit, kann es
            passieren, dass die IP des Intranators auf eine Spam-Blacklist eingetragen wird. Dann
            k&ouml;nnen viele normale E-Mails nicht mehr zugestellt werden oder landen beim Empf&auml;nger im
            Spamordner.</p></li></ul></div><p>Diese Probleme k&ouml;nnen gel&ouml;st werden, indem der Intranator E-Mails mit ung&uuml;ltigen
        Empf&auml;ngern gar nicht erst annimmt. Dann ist der sendende Server f&uuml;r die Erzeugung der
        Nichtzustellbarkeits-Nachricht zust&auml;ndig, bzw. im Falle eines Spamservers wird erst gar
        keine erzeugt.</p><p>Wird eine Domain auf dem Intranator zugestellt, kennt der Intranator alle g&uuml;ltigen
        Empf&auml;ngeradressen und lehnt ung&uuml;ltige gleich vor dem Empfang ab. Daf&uuml;r ist keine spezielle
        Konfiguration n&ouml;tig, dies geschieht vollautomatisch.</p><p>Wird eine Domain dagegen an einen anderen Server weitergeleitet, kennt nur dieser die
        g&uuml;ltigen Adressen. Damit der Intranator dennoch die E-Mails gleich beim Empfang ablehnen
        kann, gibt es die beiden im Folgenden beschriebenen Verfahren.</p><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-redirect-adresschecking-smtp"></a>15.4.2.1. Empf&auml;ngeradresspr&uuml;fung &uuml;ber SMTP-Anfragen</h4></div></div></div><a class="indexterm" name="base-email-redirect-adresschecking-smtp1"></a><a class="indexterm" name="base-email-redirect-adresschecking-smtp2"></a><p>Bevor eine E-Mail angenommen wird, fragt der Intranator kurz beim Zielserver, ob die
          Adresse g&uuml;ltig ist. F&uuml;r die &Uuml;berpr&uuml;fung wird eine SMTP-Verbindung zum Zielserver aufgebaut
          und die Zieladresse mit dem <code class="computeroutput">RCPT TO:</code>-Befehl
          &uuml;berpr&uuml;ft.</p><p>Wichtig ist hierbei, dass der Zielserver im Falle einer ung&uuml;ltigen Adresse mit einem
          Fehlercode im 500er-Bereich (z.B. <code class="computeroutput">550 Recipient address rejected: User
            unknown</code>) antwortet. Viele Server akzeptieren in der
          Standardkonfiguration die Adresse zuerst und senden dann sp&auml;ter eine
          Nichtzustellbarkeits-Nachricht. Bei einigen Servern kann das direkte Ablehnen durch eine
          Konfigurations&auml;nderung aktiviert werden. Bei machen Serverprogrammen (wie z.B. Microsoft
          Exchange vor Version 2007) ist das aber nicht m&ouml;glich. Dann ist eine
          Empf&auml;ngeradresspr&uuml;fung &uuml;ber SMTP nicht nutzbar.</p><a class="indexterm" name="d0e3873"></a><a class="indexterm" name="d0e3874"></a></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-redirect-adresschecking-ldap"></a>15.4.2.2. Empf&auml;ngeradresspr&uuml;fung &uuml;ber Active Directory und LDAP</h4></div></div></div><a class="indexterm" name="base-email-redirect-adresschecking-ldap1"></a><a class="indexterm" name="base-email-redirect-adresschecking-ldap2"></a><a class="indexterm" name="base-email-redirect-adresschecking-ldap3"></a><p>Bei diesem Verfahren fragt der Intranator regelm&auml;&szlig;ig die Liste aller g&uuml;ltigen
          E-Mail-Adressen bei einem LDAP-Server (z.B. Active Directory) ab. Beim Empfang einer
          E-Mail kann dann anhand dieser Liste sofort festgestellt werden, ob die Adresse g&uuml;ltig ist
          oder nicht.</p><p>Der Intranator ben&ouml;tigt daf&uuml;r einen g&uuml;ltigen Login auf dem LDAP-Server. Der LDAP-Login
          (bind DN) wird &uuml;blicherweise als vollst&auml;ndiger Distinguished Name eingegeben (z.B.
            <strong class="userinput"><code>CN=Benutzername, CN=Users, DC=meinefirma, DC=local</code></strong>). Viele Server
          akzeptieren aber auch einen einfachen Benutzerlogin, wenn dieser direkt in der
          LDAP-Suchbasis liegt.</p><p>Wenn Sie eine Standard-Dom&auml;ne ohne weitere Organisationseinheiten oder &auml;hnliches
          verwenden, k&ouml;nnen Sie bei Microsoft Windows Server 2000 und 2003 den Benutzer-Login als
          LDAP-Login eingeben. Bei Microsoft Windows Server 2008 geben Sie Vorname und Nachname des
          Benutzers mit Leerzeichen getrennt ein. Beides Mal w&auml;hlt der Intranator automatisch den
          passenden Distinguished Name.</p><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Es wird dringend davon abgeraten, ein Konto mit Administrationsrechten zu verwenden.
            Das Passwort muss auf dem Intranator intern im Klartext abgelegt werden und k&ouml;nnte daher
            bei einem erfolgreichen Angriff auf den Intranator verwendet werden, um auch den
            LDAP-Server zu kompromittieren.</p></td></tr></table></div><p>Die LDAP-Suchbasis ist der Ausgangspunkt f&uuml;r die Suche bei LDAP-Abfragen: Ein
          Distinguished Name (DN) des Wurzelknotens von dem zu durchsuchenden Teilbaum (z.B.
            <strong class="userinput"><code>DC=meinefirma, DC=local</code></strong> f&uuml;r die Active-Directory-Dom&auml;ne
          &#8222;meinefirma.local&#8220;).</p><p>Wenn der LDAP-Server ein Active Directory ist, stellen Sie die Struktur auf Active
          Directory. Handelt es sich um einen LDAP-Server mit anderen Schemata als bei Active
          Directory &uuml;blich, m&uuml;ssen Sie einen Suchfilter (z.B. <strong class="userinput"><code>(mail=*)</code></strong>) und
          den Namen des Ergebnisattributs (z.B. <strong class="userinput"><code>mail</code></strong>) festlegen.</p><p>Direkt nachdem die Empf&auml;ngeradresspr&uuml;fung konfiguriert wurde, versucht der Intranator
          die Daten per LDAP auszulesen. Dies muss regelm&auml;&szlig;ig wiederholt werden. Das Intervall daf&uuml;r
          wird unter Dienste&nbsp;&gt;&nbsp;E-Mail&nbsp;&gt;&nbsp;Automatik eingestellt.</p><div class="sect4" lang="de"><div class="titlepage"><div><div><h5 class="title"><a name="base-email-redirect-adresschecking-ldap-winserver"></a>15.4.2.2.1. LDAP-Pfade auf Windows-Servern</h5></div></div></div><p>Sollten Sie Schwierigkeiten haben, die passenden LDAP-Pfade f&uuml;r Ihren Windows-Server
            zu finden, wird im Folgenden beschrieben wie Sie an diese Daten herankommen.</p><div class="orderedlist"><ol type="1"><li><p>&Ouml;ffnen Sie die Management-Konsole f&uuml;r <span class="guimenuitem">Active-Directory-Benutzer und
                  -Computer</span>. Diese finden Sie normalerweise unter
                  <span class="guimenu">Verwaltung</span>.</p></li><li><p>Aktivieren Sie im Men&uuml; <span class="guimenu">Ansicht</span> die Option
                  <span class="guimenuitem">Erweiterte Features</span>.</p><div class="mediaobject"><img src="../images/base/ldaplookup-features.png"></div></li><li><p>Klicken Sie mit Rechts auf die Domain und &Ouml;ffnen den Dialog
                  <span class="guimenuitem">Eigenschaften</span>.</p></li><li><p>Im Reiter <span class="guimenu">Attribut-Editor</span> finden Sie das Attribut
                  <span class="guimenuitem">distinguishedName</span>. Diesen geben Sie im Intranator als
                LDAP-Suchbasis ein.</p><div class="mediaobject"><img src="../images/base/ldaplookup-domain.png"></div></li><li><p>Schlie&szlig;en Sie die Eigenschaftenanzeige der Domain und suchen den Pfad des
                Benutzers, den Sie zum Abrufen der Daten verwenden wollen.</p></li><li><p>Klicken Sie mit Rechts auf den Benutzer und &Ouml;ffnen den Dialog
                  <span class="guimenuitem">Eigenschaften</span>. </p></li><li><p>Im Reiter <span class="guimenu">Attribut-Editor</span> finden Sie das Attribut
                  <span class="guimenuitem">distinguishedName</span>. Diesen geben Sie im Intranator als
                LDAP-Login ein.</p><div class="mediaobject"><img src="../images/base/ldaplookup-user.png"></div></li></ol></div><a class="indexterm" name="d0e3988"></a><a class="indexterm" name="d0e3989"></a><a class="indexterm" name="d0e3990"></a><a class="indexterm" name="d0e3991"></a><a class="indexterm" name="d0e3992"></a><a class="indexterm" name="d0e3993"></a><a class="indexterm" name="d0e3994"></a></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-redirect-pop"></a>15.4.3. Weiterleitung einzelner POP-Konten</h3></div></div></div><a class="indexterm" name="base-email-redirect-pop1"></a><a class="indexterm" name="base-email-redirect-pop2"></a><a class="indexterm" name="base-email-redirect-pop3"></a><p>Sollen einzelne POP-Konten abgerufen und die E-Mails dann direkt an einen anderen Server
        weitergeleitet werden, gehen Sie wie folgt vor: Richten Sie wie unter <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-email-receive.php#base-email-receive-pop">Abschnitt&nbsp;15.3.2, &#8222;Abruf einzelner POP-Konten&#8220;</a> beschrieben das Abholen
        ein. Leiten Sie mindestens eine Domain an den entsprechenden Zielserver weiter. Wenn Sie
        nicht bereits eine Domain weiterleiten, richten Sie eine nur intern g&uuml;ltige Domain f&uuml;r
        diesen Zweck ein (z.B. <strong class="userinput"><code>net.lan</code></strong>). </p><p>Unter Dienste&nbsp;&gt;&nbsp;E-Mail&nbsp;&gt;&nbsp;Abholen w&auml;hlen Sie dann als Empf&auml;nger
        nicht einen lokalen Benutzer des Intranators aus, sondern tragen eine E-Mail-Adresse in der
        weitergeleiteten Domain ein. Die E-Mails aus dem POP-Konto werden dann nach den &uuml;blichen
        Filtern (Viren, Anh&auml;nge, Spam) an die eingegebene Adresse auf dem Zielserver
        zugestellt.</p><a class="indexterm" name="d0e4026"></a><a class="indexterm" name="d0e4027"></a><a class="indexterm" name="d0e4028"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-email-receive.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-email.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-email-addressing.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">15.3. E-Mail-Empfang auf dem Intranator&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;15.5. E-Mail-Adressierung</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>