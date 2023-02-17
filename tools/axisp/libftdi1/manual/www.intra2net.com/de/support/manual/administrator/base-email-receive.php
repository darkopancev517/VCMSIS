<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>E-Mail-Empfang auf dem Intranator | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-email.php" title="15. Kapitel - E-Mail"><link rel="prev" href="base-email-receive-client.php" title="15.2. E-Mail-Empfang auf dem Client (POP oder IMAP)"><link rel="next" href="base-email-redirect.php" title="15.4. Weiterleitung von gesamten Domains">
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

<a href="base-email-receive.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-email-receive.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">15.3. E-Mail-Empfang auf dem Intranator</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-email-receive-client.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">15. Kapitel - E-Mail</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-email-redirect.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-email-receive"></a>15.3. E-Mail-Empfang auf dem Intranator</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-receive-concepts"></a>15.3.1. Konzepte</h3></div></div></div><p>Es gibt 3 verschiedene Konzepte, wie eingehende E-Mails auf den Intranator kommen
        k&ouml;nnen.</p><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-receive-concepts-pop"></a>15.3.1.1. Abruf einzelner POP-Konten</h4></div></div></div><a class="indexterm" name="base-email-receive-concepts-pop1"></a><a class="indexterm" name="base-email-receive-concepts-pop2"></a><div class="mediaobject"><img src="../images/base/email-receive-concept-pop.png"></div><p>Bei einem Provider wird f&uuml;r jede E-Mail-Adresse ein eigenes POP-Postfach angelegt. Der
          Intranator holt jedes dieser Postf&auml;cher separat ab und stellt den Inhalt an den Empf&auml;nger
          zu.</p><p>Vorteile:</p><div class="itemizedlist"><ul type="disc"><li><p>Bei fast allen Providern verf&uuml;gbar</p></li><li><p>Keine Nichtzustellbarkeits-E-Mails (Bounces), da der Provider alle g&uuml;ltigen
              Adressen kennt</p></li></ul></div><p>Nachteile:</p><div class="itemizedlist"><ul type="disc"><li><p>Bei vielen Konten h&ouml;herer Administrationsaufwand</p></li><li><p>Konten werden sequentiell abgearbeitet; bei hoher Anzahl an Konten daher h&ouml;herer
              Zeitbedarf</p></li></ul></div><a class="indexterm" name="d0e3567"></a><a class="indexterm" name="d0e3568"></a></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-receive-concepts-smtp"></a>15.3.1.2. Direkte Zustellung per SMTP</h4></div></div></div><a class="indexterm" name="base-email-receive-concepts-smtp1"></a><a class="indexterm" name="base-email-receive-concepts-smtp2"></a><div class="mediaobject"><img src="../images/base/email-receive-concept-smtp.png"></div><p>Der Absender sendet die E-Mails direkt und ohne zwischengeschalteten Provider zum
          Intranator.</p><p>Vorteile:</p><div class="itemizedlist"><ul type="disc"><li><p>Neue E-Mails kommen sofort an</p></li><li><p>Keine Nichtzustellbarkeits-E-Mails (Bounces)</p></li></ul></div><p>Nachteile:</p><div class="itemizedlist"><ul type="disc"><li><p>Es wird eine fest zugewiesene IP-Adresse ben&ouml;tigt</p></li></ul></div><a class="indexterm" name="d0e3604"></a><a class="indexterm" name="d0e3605"></a></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-receive-concepts-multidrop"></a>15.3.1.3. Abruf von POP-Sammelkonten (Multidrop, Catch-All)</h4></div></div></div><a class="indexterm" name="base-email-receive-concepts-multidrop1"></a><a class="indexterm" name="base-email-receive-concepts-multidrop2"></a><a class="indexterm" name="base-email-receive-concepts-multidrop3"></a><div class="mediaobject"><img src="../images/base/email-receive-concept-multidrop.png"></div><p>Alle E-Mails f&uuml;r eine Domain werden bei einem Provider in einem einzigen POP-Konto
          gesammelt. Der Intranator ruft dieses eine Konto ab und teilt die E-Mails dann auf die
          passenden Empf&auml;nger auf.</p><p>Vorteile:</p><div class="itemizedlist"><ul type="disc"><li><p>Geringerer Administrationsaufwand, da beim Provider nur ein Konto gepflegt werden
              muss.</p></li></ul></div><p>Nachteile:</p><div class="itemizedlist"><ul type="disc"><li><p>Kein Standard f&uuml;r Multidrop-Kopfzeile</p></li><li><p>Nur bei sehr wenigen Provider funktioniert es vollst&auml;ndig (Mehrere Empf&auml;nger in
              einer Domain, BCC, ...)</p></li><li><p>Nichtzustellbarkeits-E-Mails (Bounces) nicht vermeidbar</p></li></ul></div><a class="indexterm" name="d0e3643"></a><a class="indexterm" name="d0e3644"></a><a class="indexterm" name="d0e3645"></a></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-receive-concepts-recommendation"></a>15.3.1.4. Empfehlung</h4></div></div></div><p>Wir empfehlen bis zu einer Anzahl von ca. 15 Benutzern den Abruf einzelner POP-Konten.
          Bei mehr Benutzern bietet sich dann die direkte Zustellung per SMTP an.</p><p>Von der Verwendung von POP-Sammelkonten (Multidrop, Catch-All) raten wir generell
          ab.</p></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-receive-pop"></a>15.3.2. Abruf einzelner POP-Konten</h3></div></div></div><a class="indexterm" name="base-email-receive-pop1"></a><a class="indexterm" name="base-email-receive-pop2"></a><p>Sollen E-Mails von einem einzelnen POP3-Konto bei einem Provider abgeholt werden, so
        kann dies unter Dienste&nbsp;&gt;&nbsp;E-Mail&nbsp;&gt;&nbsp;Abholen konfiguriert werden. Es
        k&ouml;nnen f&uuml;r einen Benutzer beliebig viele externe Konten eingetragen werden.</p><p>Unter <span class="guimenuitem">Verschl&uuml;sselung</span> kann eingestellt werden, wie weit die
        Verbindung zum Server verschl&uuml;sselt wird. Bei manchen schlecht konfigurierten Servern f&uuml;hrt
        die automatische Verschl&uuml;sselungserkennung zu Problemen beim Verbindungsaufbau. Hierf&uuml;r ist
        der Modus "Keine" Verschl&uuml;sselung gedacht.</p><a class="indexterm" name="d0e3675"></a><a class="indexterm" name="d0e3676"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-receive-smtp"></a>15.3.3. Direkte Zustellung per SMTP</h3></div></div></div><a class="indexterm" name="base-email-receive-smtp1"></a><a class="indexterm" name="base-email-receive-smtp2"></a><p>Haben Sie eine feste IP, ist es m&ouml;glich die E-Mails direkt vom Absender zum Intranator
        senden zu lassen. Dazu m&uuml;ssen Sie Ihre statische IP von Ihrem Domain-Provider (normalerweise
        der, der auch f&uuml;r die Webseite zust&auml;ndig ist) als MX
          <span class="foreignphrase"><em class="foreignphrase">(MaileXchange)</em></span> in der Domain eintragen lassen. Au&szlig;erdem
        m&uuml;ssen Sie den SMTP-Port in der Firewall &ouml;ffnen (siehe <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="firewall-profiles-provider.php">Abschnitt&nbsp;34.3, &#8222;Providerprofile&#8220;</a>).</p><p>Die direkte Zustellung von eingehenden E-Mails per SMTP ist vollkommen unabh&auml;ngig vom
        Versand der E-Mails. Die strengen Kriterien f&uuml;r den direkten E-Mail-Versand aus <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-email.php#base-email-send-direct">Abschnitt&nbsp;15.1.5, &#8222;Direkter Versand&#8220;</a> haben hier keine
        Relevanz und ein Versand &uuml;ber Relayserver ist problemlos m&ouml;glich.</p><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Verwenden Sie den Intranator mit dynamischen IPs und DynDNS auf keinen Fall zum
          direkten Empfang per SMTP, auch wenn einige DynDNS-Provider dies anbieten, denn beim
          Wechsel der IP oder einer Leitungsst&ouml;rung k&ouml;nnen Fremde Ihre E-Mails empfangen.</p></td></tr></table></div><a class="indexterm" name="d0e3706"></a><a class="indexterm" name="d0e3707"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-receive-multidrop"></a>15.3.4. Abruf von POP-Sammelkonten (Multidrop)</h3></div></div></div><a class="indexterm" name="base-email-receive-multidrop1"></a><a class="indexterm" name="base-email-receive-multidrop2"></a><a class="indexterm" name="base-email-receive-multidrop3"></a><p>Der Intranator kann die E-Mails f&uuml;r eine Domain per Multidrop aus einem POP3 Konto
        abholen und dann verteilen.</p><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Wegen der massiven Nachteile (siehe oben) r&auml;t Intra2net von der Verwendung dieses
          Verfahrens generell ab!</p></td></tr></table></div><p>Der Provider muss die M&ouml;glichkeit anbieten, alle E-Mails f&uuml;r eine Domain in ein Konto zu
        speichern oder einen &#8222;Catch-All&#8220; Account einzurichten, an den alle E-Mails mit unbekanntem
        Empf&auml;nger gehen.</p><p>Au&szlig;erdem wird zum Verteilen ein sog. Multidrop Header ben&ouml;tigt, den der Mailserver des
        Providers in den Kopf der E-Mail einf&uuml;gen muss. In ihm wird der wirkliche Empf&auml;nger
        (Envelope / RCPT-To) der E-Mail gesichert.</p><p>Es gibt jedoch verschiedene Typen von Multidrop-Headern:</p><div class="informaltable"><table border="1"><colgroup><col align="left"><col align="left"></colgroup><tbody><tr><td align="left">Normaler Header</td><td align="left">Er hei&szlig;t z.B. X-Envelope-To:, Envelope-to:, X-Original-To: oder X-RCPT-To: und
                enth&auml;lt nur die E-Mail-Adresse des Empf&auml;ngers. Dieser Typ wird haupts&auml;chlich von der
                Exim Software angeboten. Tragen Sie den Namen des Headers (mit Doppelpunkt) in das
                &#8222;Multidrop Header&#8220; Feld ein.</td></tr><tr><td align="left">Qvirtual</td><td align="left">Er hei&szlig;t Delivered-To: und wird haupts&auml;chlich von Qmail verwendet. Er enth&auml;lt
                vor der eigentlichen Empf&auml;ngeradresse eine Domainkennung. Tragen Sie die
                Domainkennung in das &#8222;Multidrop Header&#8220; Feld ein. Beispiele daf&uuml;r sind
                &#8222;mbox-ihredomain.de-&#8220; oder &#8222;ihredomain.de-&#8220;</td></tr><tr><td align="left">Received</td><td align="left">Die E-Mail enth&auml;lt keinen Multidrop-Header. Der Intranator versucht, die
                Empf&auml;ngeradresse aus den Recieved-Informationen im Header zu ermitteln. Dies kann
                bei manchen Providern zu Problemen f&uuml;hren. Einige E-Mails werden dann an den
                Postmaster (siehe <a class="xref" href="base-email-configuration.php" title="15.11. Weitere Einstellungen">Abschnitt&nbsp;15.11, &#8222;Weitere Einstellungen&#8220;</a>) zugestellt. Diese
                Option ist daher nur als Notl&ouml;sung gedacht, falls ein Provider keinen
                Multidrop-Header &uuml;bertr&auml;gt.</td></tr></tbody></table></div><div class="tip" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Tip"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Tipp]" src="../images/admon/tip.png"></td><th align="left">Tipp</th></tr><tr><td align="left" valign="top"><p>Ist der Provider nicht in der Lage, zuverl&auml;ssig Envelope-Header einzuf&uuml;gen, so
          empfiehlt es sich, bei einem anderen Provider (z.B. 1&amp;1) f&uuml;r wenige Euro pro Monat
          eine Domain extra f&uuml;r den Mailempfang einzurichten (z.B. &#8222;meinefirma-mail.de&#8220;). Der
          bisherige Provider kann dann alle E-Mails an die Domain 1:1 an die neue Domain
          weiterleiten.</p></td></tr></table></div><div class="example"><a name="d0e3758"></a><p class="title"><b>Beispiel 15.1. Beispielausschnitt aus einem E-Mail-Header mit normalem Envelope-Header</b></p><div class="example-contents"><pre class="programlisting">Received: from localhost (localhost.localdomain [127.0.0.1])
&nbsp;&nbsp;&nbsp;&nbsp;by fire.local (8.11.6/8.11.6) with ESMTP id g3SMO2D10977
&nbsp;&nbsp;&nbsp;&nbsp;for &lt;gerd@localhost&gt;; Mon, 29 Apr 2002 00:24:02 +0200
Envelope-to: gerd@klickmich.de
Delivery-date: Sun, 28 Apr 2002 21:22:01 +0200
Received: from pop.kundenserver.de [212.227.126.129]
&nbsp;&nbsp;&nbsp;&nbsp;by localhost with POP3 (fetchmail-5.9.0)
&nbsp;&nbsp;&nbsp;&nbsp;for gerd@localhost (single-drop); Mon, 29 Apr 2002 00:24:02 +0200 (CEST)
Received: from [4.43.46.11] (helo=intranator.net.local)
&nbsp;&nbsp;&nbsp;&nbsp;by mxng00.kundenserver.de with smtp (Exim 3.22 #2)
&nbsp;&nbsp;&nbsp;&nbsp;id 171uF3-0007Sd-00
&nbsp;&nbsp;&nbsp;&nbsp;for gerd@klickmich.de; Sun, 28 Apr 2002 21:21:50 +0200
Message-Id: &lt;j60jo.a5626@intranator.net.local&gt;
To: gerd@klickmich.de
Subject: Test</pre></div></div><br class="example-break"><p>Das einfache To: ist kein Multidrop-Header!</p><div class="example"><a name="d0e3766"></a><p class="title"><b>Beispiel 15.2. Beispielausschnitt aus einem E-Mail-Header mit Qvirtual-Header</b></p><div class="example-contents"><pre class="programlisting">Return-Path: &lt;k.schuster@irgendwo.de&gt;
Delivered-To: klickmich.de-m.muster@klickmich.de
Received: (qmail 29628 invoked from network); 30 Jun 2002 14:47:38 -0000
Received: from moutng1.kundenserver.de (212.227.126.171)
&nbsp;&nbsp;&nbsp;&nbsp;by pluto.link-m.de with SMTP; 30 Jun 2002 14:47:39 -0000
Received: from [212.227.126.162] (helo=mrelayng1.schlund.de)
&nbsp;&nbsp;&nbsp;&nbsp;by moutng1.kundenserver.de with esmtp (Exim 3.22 #2)
&nbsp;&nbsp;&nbsp;&nbsp;id 17OfzF-0003jP-00
&nbsp;&nbsp;&nbsp;&nbsp;for m.muster@klickmich.de; Sun, 30 Jun 2002 16:47:37 +0200
Received: from [217.81.153.239] (helo=intranator.net.local)
&nbsp;&nbsp;&nbsp;&nbsp;by mrelayng1.schlund.de with asmtp (Exim 3.35 #1)
&nbsp;&nbsp;&nbsp;&nbsp;id 17OfzF-0002Mf-00
&nbsp;&nbsp;&nbsp;&nbsp;for m.muster@klickmich.de; Sun, 30 Jun 2002 16:47:37 +0200
Received: from storm (storm.net.local [172.16.1.2])
&nbsp;&nbsp;&nbsp;&nbsp;by intranator.net.local (8.11.6/8.11.6) with SMTP id g5UElmD25862
&nbsp;&nbsp;&nbsp;&nbsp;for &lt;m.muster@klickmich.de&gt; Sun, 30 Jun 2002 16:47:48 +0200
Message-ID: &lt;001d01c22045$12856700$020110ac@storm&gt;
From: "Karl Schuster" &lt;k.schuster@irgendwo.de&gt;
To: &lt;m.muster@klickmich.de&gt;
Subject: Beispiel</pre></div></div><br class="example-break"><p>Interessant ist hier der &#8222;Delivered-To:&#8220; Header. In diesem Beispiel ist die
        Domainkennung &#8222;klickmich.de-&#8220;. Tragen Sie diese in das &#8222;Multidrop-Header&#8220; Feld im Intranator
        ein.</p><p>Wird der Multidrop-Header nicht korrekt eingestellt, so werden alle E-Mails, bei denen
        nicht der wirkliche Empf&auml;nger in To: steht, an den Postmaster geschickt. Dies sind z.B.
        E-Mails mit BCC:, weitergeleitete E-Mails, E-Mails von Mailinglisten oder Spam.</p><a class="indexterm" name="d0e3776"></a><a class="indexterm" name="d0e3777"></a><a class="indexterm" name="d0e3778"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-email-receive-client.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-email.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-email-redirect.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">15.2. E-Mail-Empfang auf dem Client (POP oder IMAP)&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;15.4. Weiterleitung von gesamten Domains</td></tr></table></div>
      
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