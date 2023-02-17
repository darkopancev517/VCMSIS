<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Freigaben und Zugriff auf fremde Ordner | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client.php" title="Teil&nbsp;3.&nbsp;Groupware Client"><link rel="prev" href="groupware-client-account-import.php" title="20.3. Bestehende Daten &uuml;bernehmen"><link rel="next" href="groupware-client-access-subscribe.php" title="21.2. Fremde Ordner verbinden">
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

<a href="groupware-client-access.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-access.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">21. Kapitel - Freigaben und Zugriff auf fremde Ordner</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-account-import.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;3.&nbsp;Groupware Client</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="groupware-client-access-subscribe.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="groupware-client-access"></a>21. Kapitel - Freigaben und Zugriff auf fremde Ordner</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="groupware-client-access.php#groupware-client-access-permit">21.1. Eigene Ordner freigeben</a></span></dt><dd><dl><dt><span class="sect2"><a href="groupware-client-access.php#groupware-client-access-permit-shared-seen">21.1.1. Gelesen-Status gemeinsam/individuell</a></span></dt></dl></dd><dt><span class="sect1"><a href="groupware-client-access-subscribe.php">21.2. Fremde Ordner verbinden</a></span></dt><dt><span class="sect1"><a href="ch21s03.php">21.3. Mehrere Serverkonten</a></span></dt></dl></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-access-permit"></a>21.1. Eigene Ordner freigeben</h2></div></div></div><a class="indexterm" name="groupware-client-access-permit1"></a><a class="indexterm" name="groupware-client-access-permit2"></a><a class="indexterm" name="groupware-client-access-permit3"></a><a class="indexterm" name="groupware-client-access-permit4"></a><p>Damit andere Benutzer auf einen Ordner zugreifen k&ouml;nnen, muss der Eigent&uuml;mer ihn
            zuerst wie folgt freigeben:</p><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie das Men&uuml; <span class="guimenu">Groupware Client&nbsp;&gt;&nbsp;Meine
                        Freigaben</span>.</p></li><li><p>Klicken Sie auf der linken Seite (Server-Konten) den freizugebenden Ordner
                    an.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/access-permit01.png"></div></div></li><li><p>Machen Sie einen Doppelklick auf der rechten Seite (Meine Freigaben). Es
                    erscheint der Dialog f&uuml;r eine neue Freigabe. Markieren Sie den Benutzernamen
                    oder die Benutzergruppe, f&uuml;r die Sie den Ordner freigeben m&ouml;chten.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/access-permit02.png"></div></div></li><li><p>W&auml;hlen Sie mit den Checkboxen am unteren Rand des Dialogs die Rechte, die Sie
                    dem anderen Benutzer erteilen m&ouml;chten.</p></li><li><p>Klicken Sie auf <span class="guibutton">Speichern</span>, um die neuen Rechte auf den
                    Server zu schreiben.</p></li></ol></div><p>Es empfiehlt sich, die Freigaben nicht f&uuml;r einzelne Benutzer, sondern f&uuml;r
            Benutzergruppen auf dem Intranator Server zu erteilen. Dies vereinfacht die Verwaltung
            der Freigaben vor allem bei Benutzerfluktuation und Umstrukturierung.</p><p>Die einzelnen Rechte haben folgende Bedeutung:</p><div class="informaltable"><table border="1"><colgroup><col><col></colgroup><tbody><tr><td>
                            <p>Lesen</p>
                        </td><td>
                            <p>Der Benutzer kann den Ordner und all seine Inhalte sehen.</p>
                        </td></tr><tr><td>
                            <p>Schreiben</p>
                        </td><td>
                            <p>Der Benutzer darf neue Eintr&auml;ge in diesem Ordner anlegen und
                                bestehende &auml;ndern oder l&ouml;schen.</p>
                        </td></tr><tr><td>
                            <p>Ordner</p>
                        </td><td>
                            <p>Der Benutzer darf den Ordner l&ouml;schen und umbenennen sowie neue
                                Unterordner unterhalb dieses Ordners anlegen. Au&szlig;erdem bekommt der
                                Benutzer Administrationsrechte auf den Ordner und darf die Freigaben
                                an andere Benutzer ver&auml;ndern.</p>
                        </td></tr><tr><td>
                            <p>Kennzeichnungen</p>
                        </td><td>
                            <p>Der Benutzer darf die Kennzeichnungen Gelesen, Beantwortet und
                                Nachverfolgung (ohne Datum, Flaggensymbol in Outlook) der
                                bestehenden Inhalte &auml;ndern.</p>
                        </td></tr></tbody></table></div><p>Die eingestellten Rechte gelten normalerweise nur f&uuml;r den markierten Ordner selbst.
            &Uuml;ber die entsprechende Option k&ouml;nnen die f&uuml;r den markierten Ordner eingestellten Rechte
            auch f&uuml;r alle Unterordner &uuml;bernommen werden. Dabei werden nicht nur die momentan
            ge&auml;nderten Rechte angepasst, sondern die kompletten, f&uuml;r den markierten Ordner gesetzten
            Rechte, bei allen Unterordnern &uuml;bernommen.</p><p>Neu angelegte Ordner &uuml;bernehmen beim Anlegen immer die Rechte ihres
            &Uuml;berordners.</p><a class="indexterm" name="d0e7252"></a><a class="indexterm" name="d0e7253"></a><a class="indexterm" name="d0e7254"></a><a class="indexterm" name="d0e7255"></a><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-access-permit-shared-seen"></a>21.1.1. Gelesen-Status gemeinsam/individuell</h3></div></div></div><a class="indexterm" name="groupware-client-access-permit-shared-seen1"></a><p>Der Intranator Server bietet die M&ouml;glichkeit, den Status "gelesen" oder
                "ungelesen" von neu eingegangenen E-Mails entweder f&uuml;r alle Nutzer gemeinsam zu
                verwalten, oder f&uuml;r jeden Nutzer mit Zugriffsrechten auf diesen Ordner individuell.
                Welche Variante besser geeignet ist, h&auml;ngt vom Nutzungsszenario und dem Grund f&uuml;r
                die Freigabe eines E-Mail-Ordners an andere Nutzer ab. Daher k&ouml;nnen beide Varianten
                eingestellt werden.</p><p>Wird im Men&uuml; <span class="guimenu">Groupware Client&nbsp;&gt;&nbsp;Meine Freigaben</span>
                eine neue Freigabe an andere Nutzer mit dem Recht "Kennzeichnungen" gesetzt, wird
                automatisch der gemeinsame Gelesen-Status aktiviert. </p><p>Soll der Gelesen-Status individuell pro Benutzer verwaltet werden, so &ouml;ffnen Sie
                das Kontextmen&uuml; des Ordners &uuml;ber einen Rechtsklick und schalten die Option
                    <span class="guimenuitem"> Gelesen Status mit anderen teilen</span> aus.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/set-shared-seen.png"></div></div><a class="indexterm" name="d0e7280"></a></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-account-import.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="groupware-client-access-subscribe.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">20.3. Bestehende Daten &uuml;bernehmen&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;21.2. Fremde Ordner verbinden</td></tr></table></div>
      
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